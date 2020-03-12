//gcc -o render render.c `sdl-config --libs` -lGL -lGLU -lglut
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

/* screen width, height, and bit depth */

/* Set up some booleans */
#define TRUE  1
#define FALSE 0

typedef struct ponto{
    float x,y,z;
}Ponto;

typedef struct face{
    int p1, p2, p3, p4;
}Face;

typedef struct normal{
    float x,y,z;
}Normal;

typedef struct objeto {
    int quantP, quantF, quantN;
    int maxQuantP, maxQuantF, maxQuantN;
    Ponto *pontos;
    Face *faces;
    Normal *normais;
}Objeto;

float anguloX = 0.0f, anguloY = 0.0f, anguloZ = 0.0f;
Objeto *ob;

void inicializaFaces(Face *f, int qf) {
    int i;
    for(i=0 ; i<qf ; i++) {
        f->p1 = -1;
        f->p2 = -1;
        f->p3 = -1;
        f->p4 = -1;
    }
}

void inicializaPontos(Ponto *p, int qp) {
    int i;
    for(i=0 ; i<qp ; i++) {
        p->x = -1;
        p->y = -1;
        p->z = -1;
    }
}

void inicializaNormais(Normal *pn, int qn) {
    int i;
    for(i=0 ; i<qn ; i++) {
        pn->x = -1;
        pn->y = -1;
        pn->z = -1;
    }
}

void mostraPontos(Objeto *ob) {
    int i;
    printf("Pontos:\n");
    for(i=0 ; i<ob->quantP ; i++) {
        printf("Ponto[%i] x=%f|y=%f|z=%f\n", i, (ob->pontos)[i].x, (ob->pontos)[i].y, (ob->pontos)[i].z);
    }
}

void mostraNormais(Objeto *ob) {
    int i;
    printf("Normais:\n");
    for(i=0 ; i<ob->quantN ; i++) {
        printf("Normal[%i] x=%f|y=%f|z=%f\n", i, (ob->normais)[i].x, (ob->normais)[i].y, (ob->normais)[i].z);
    }
}

void mostraFaces(Objeto *ob) {
    int i;
    printf("Faces:\n");
    for(i=0 ; i<ob->quantF ; i++) {
        printf("Face[%i] p1=%i|p2=%i|p3=%i|p4=%i\n", i, (ob->faces)[i].p1, (ob->faces)[i].p2, (ob->faces)[i].p3, (ob->faces)[i].p4);
    }
}



Objeto* criaObjeto() {
    Objeto *ob = malloc(sizeof(Objeto));
    ob->maxQuantF = 20;
    ob->maxQuantP = 20;
    ob->maxQuantN = 20;
    ob->quantF = 0;
    ob->quantP = 0;
    ob->quantN = 0;
    ob->pontos = malloc(ob->maxQuantP * sizeof(Ponto));
    ob->faces = malloc(ob->maxQuantF * sizeof(Face));
    ob->normais = malloc(ob->maxQuantN * sizeof(Normal));
    inicializaPontos(ob->pontos, ob->maxQuantP);
    inicializaFaces(ob->faces, ob->maxQuantF);
    inicializaNormais(ob->normais, ob->maxQuantN);
    return ob;
}

void destroiObjeto(Objeto *ob) {
    free(ob->pontos);
    free(ob->normais);
    free(ob->faces);
}

void inserePonto(Objeto *ob, float x, float y, float z) {
    (ob->pontos)[ob->quantP].x = x;
    (ob->pontos)[ob->quantP].y = y;
    (ob->pontos)[ob->quantP].z = z;
    ob->quantP++;
}

void insereNormal(Objeto *ob, float x, float y, float z) {
    (ob->normais)[ob->quantN].x = x;
    (ob->normais)[ob->quantN].y = y;
    (ob->normais)[ob->quantN].z = z;
    ob->quantN++;
}

void insereFace(Objeto *ob, int p1, int p2, int p3, int p4) {
    (ob->faces)[ob->quantF].p1 = p1;
    (ob->faces)[ob->quantF].p2 = p2;
    (ob->faces)[ob->quantF].p3 = p3;
    (ob->faces)[ob->quantF].p4 = p4;
    ob->quantF++;
}

void OBJ_Reading(char *arqEntrada, Objeto *ob) {
    FILE *arq;
    char buffer[100];
    float x,y,z;
    int p1,p2,p3,p4;
    if((arq = fopen(arqEntrada, "r")) != NULL) {
        while(feof(arq) == 0) {
            fscanf(arq, "%s", buffer);
            if(buffer[0] == 'v' && buffer[1] == '\0') {
                fscanf(arq, "%f", &x);
                fscanf(arq, "%f", &y);
                fscanf(arq, "%f", &z);
                inserePonto(ob, x, y, z);
            }else if(buffer[0] == 'f' && buffer[1] == '\0'){//vertices
                fscanf(arq, "%s", buffer);
                p1 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p2 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p3 = (int)(buffer[0]-'0');
                fscanf(arq, "%s", buffer);
                p4 = (int)(buffer[0]-'0');
                insereFace(ob, p1, p2, p3, p4);
            }else if(buffer[0] == 'v' && buffer[1] == 'n' && buffer[2] == '\0') {
                fscanf(arq, "%f", &x);
                fscanf(arq, "%f", &y);
                fscanf(arq, "%f", &z);
                insereNormal(ob, x, y, z);
            }
        }
        fclose(arq);
    }else {
        printf("ERRO ARQUIVO\n");
    }

}

/* This is our SDL surface */
SDL_Surface *surface;

/* Whether or not lighting is on */
int light = FALSE;

GLfloat xrot;
GLfloat yrot;
GLfloat xspeed;
GLfloat yspeed;
GLfloat z = -5.0f;

GLfloat LightAmbient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 0.0f };

GLuint filter;
GLuint texture[7];

void Quit( int returnCode )
{
    SDL_Quit( );
    exit( returnCode );
}
int LoadGLTextures( )
{
    int i;
    int Status = FALSE;
    SDL_Surface *TextureImage[7];

    glGenTextures( 7, texture );
    if (( TextureImage[0] = SDL_LoadBMP( "baixo.bmp" ) )) {
	    Status = TRUE;
	    glBindTexture( GL_TEXTURE_2D, texture[0] );
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[0]->w,
			  TextureImage[0]->h, 0, GL_BGR,
			  GL_UNSIGNED_BYTE, TextureImage[0]->pixels );

	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );

    }

	if (( TextureImage[1] = SDL_LoadBMP( "esquerda.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[1] );
	    glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[1]->w, TextureImage[1]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, TextureImage[1]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
    }

	if (( TextureImage[2] = SDL_LoadBMP( "cima.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[2] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[2]->w, TextureImage[2]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, TextureImage[2]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
    }

	if (( TextureImage[3] = SDL_LoadBMP( "direita.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[3] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[3]->w, TextureImage[3]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, TextureImage[3]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}

	if (( TextureImage[4] = SDL_LoadBMP( "abertura1.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[4] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[4]->w, TextureImage[4]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, TextureImage[4]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}

	if (( TextureImage[5] = SDL_LoadBMP( "baixo.bmp" ) )) {
    	glBindTexture( GL_TEXTURE_2D, texture[5] );
    	glTexImage2D( GL_TEXTURE_2D, 0, 3, TextureImage[5]->w, TextureImage[5]->h, 0, GL_BGR,
                  GL_UNSIGNED_BYTE, TextureImage[5]->pixels );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			     GL_NEAREST );
	    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			     GL_NEAREST );
	}

    for(i=0;i<6;i++)
    	if ( TextureImage[i] )
	    	SDL_FreeSurface( TextureImage[i] );

    return Status;
}
int resizeWindow( int width, int height )
{
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLint )width, ( GLint )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );

    return( TRUE );
}

/* function to handle key press events */
void handleKeyPress( SDL_keysym *keysym )
{
    switch ( keysym->sym )
	{
	case SDLK_ESCAPE:
	    /* ESC key was pressed */
	    Quit( 0 );
	    break;
	case SDLK_UP:
	    /* Up arrow key was pressed
	     * this affects the x rotation
	     */
	    xspeed = 0.3f;
	    break;
	case SDLK_DOWN:
	    /* Down arrow key was pressed
	     * this affects the x rotation
	     */
	    xspeed = 0.3f;
	    break;
	case SDLK_RIGHT:
	    /* Right arrow key was pressed
	     * this affects the y rotation
	     */
	    yspeed = 0.3f;
	    break;
	case SDLK_LEFT:
	    /* Left arrow key was pressed
	     * this affects the y rotation
	     */
	    yspeed = 0.3f;
	    break;
	default:
	    break;
	}

    return;
}

/* general OpenGL initialization function */
int initGL( GLvoid )
{

    ob = criaObjeto();
    OBJ_Reading("brute.obj", ob);
    if ( !LoadGLTextures( ) )
	return FALSE;
    glEnable( GL_TEXTURE_2D );
    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0f, 0.0f,0.0f, 0.0f );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glLightfv( GL_LIGHT1, GL_AMBIENT, LightAmbient );
    return( TRUE );
}

int drawGLScene( GLvoid )
{
    static GLint T0     = 0;
    static GLint Frames = 0;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity( );
	  glTranslatef (-1, -2, -7);
	  glTranslatef (0.90, 1.9, -2.1);
	  glRotatef(270,0,0,1);
    glRotatef( yrot, 1.0f, 0.0f, 0.0f);
    glRotatef( xrot, 0.0f, 1.0f, 0.0f);
    glTranslatef (-0.90, -1.9, 2.1);
    glBindTexture( GL_TEXTURE_2D, texture[0] );

	int i;
    for(i=0 ; i<ob->quantF ; i++) {
    	glBindTexture( GL_TEXTURE_2D, texture[i] );
        glBegin(GL_QUADS);
        glNormal3f( -1.0f, 0.0f, 0.0f );
        glTexCoord2f( 1.0f, 1.0f );glVertex3f(ob->pontos[ob->faces[i].p1-1].x, ob->pontos[ob->faces[i].p1-1].y, ob->pontos[ob->faces[i].p1-1].z);
        glTexCoord2f( 1.0f, 0.0f );glVertex3f(ob->pontos[ob->faces[i].p2-1].x, ob->pontos[ob->faces[i].p2-1].y, ob->pontos[ob->faces[i].p2-1].z);
        glTexCoord2f( 0.0f, 0.0f );glVertex3f(ob->pontos[ob->faces[i].p3-1].x, ob->pontos[ob->faces[i].p3-1].y, ob->pontos[ob->faces[i].p3-1].z);
        glTexCoord2f( 0.0f, 1.0f );glVertex3f(ob->pontos[ob->faces[i].p4-1].x, ob->pontos[ob->faces[i].p4-1].y, ob->pontos[ob->faces[i].p4-1].z);
        glEnd();
    }
    SDL_GL_SwapBuffers( );

    xrot += xspeed*3;
    yrot += yspeed*3;

    return( TRUE );
}

int main( int argc, char **argv )
{
    int videoFlags;
    int done = FALSE;
    SDL_Event event;
    const SDL_VideoInfo *videoInfo;
    int isActive = TRUE;
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
	    fprintf( stderr, "Video initialization failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}
    videoInfo = SDL_GetVideoInfo( );
    if ( !videoInfo )
	{
	    fprintf( stderr, "Video query failed: %s\n",
		     SDL_GetError( ) );
	    Quit( 1 );
	}

    /* the flags to pass to SDL_SetVideoMode */
    videoFlags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    videoFlags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    videoFlags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    videoFlags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( videoInfo->hw_available )
	videoFlags |= SDL_HWSURFACE;
    else
	videoFlags |= SDL_SWSURFACE;

    if ( videoInfo->blit_hw )
	videoFlags |= SDL_HWACCEL;

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    surface = SDL_SetVideoMode( 800, 750,25,	videoFlags );

    if ( !surface )
	{
	    fprintf( stderr,  "Video mode set failed: %s\n", SDL_GetError( ) );
	    Quit( 1 );
	}

    initGL( );

    resizeWindow( 800, 750 );

    while ( !done )
	{
	    while ( SDL_PollEvent( &event ) )
		{
		    switch( event.type )
			{
			case SDL_ACTIVEEVENT:
			    if ( event.active.gain == 0 )
				isActive = FALSE;
			    else
				isActive = TRUE;
			    break;
			case SDL_VIDEORESIZE:
			    surface = SDL_SetVideoMode( event.resize.w,
							event.resize.h,
							16, videoFlags );

			    resizeWindow( event.resize.w, event.resize.h );
			    break;
			case SDL_KEYDOWN:
			    /* handle key presses */
			    handleKeyPress( &event.key.keysym );
			    break;
			case SDL_QUIT:
			    done = 1;
			    break;
			default:
			    break;
			}
		}
	    if ( isActive )
		drawGLScene( );
	}
    Quit( 0 );

    return( 0 );
}
