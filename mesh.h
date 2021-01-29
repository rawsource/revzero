#ifndef RZ_MESH_H
#define RZ_MESH_H

#include <string>

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

struct Vertex
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

struct Color
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

struct Mesh
{
	int size;
	GLfloat alpha;
	std::string name;
	Vertex* vertices;
	Color* colors;
	void render(float x, float y, float angle, float scale, bool hit=false)
	{
		glPushMatrix();
		glTranslatef( x, y, 0 );
		glScalef( scale, scale, scale);
		glRotatef( -angle, 0, 0, 1 );

		// set color data
		if (! hit)
		{
			//glBindBuffer(GL_ARRAY_BUFFER, 1);
			//glBufferData(GL_ARRAY_BUFFER, size * sizeof(Color), &colors[0].r, GL_STREAM_DRAW);
			glColorPointer( 4, GL_FLOAT, 0, colors );
		}
		else
		{
			glDisableClientState( GL_COLOR_ARRAY );
			glColor3f(1, 1, 1);
		}

		//glBindBuffer( GL_ARRAY_BUFFER, 0 );
		//glBufferData( GL_ARRAY_BUFFER, size * sizeof(Vertex), &vertices[0].x, GL_STATIC_DRAW );

		// set vertex data
		glVertexPointer( 3, GL_FLOAT, 0, vertices );

		// draw quad using vertex data
		glDrawArrays( GL_TRIANGLES, 0, size );

		if (hit) {
			glEnableClientState( GL_COLOR_ARRAY );
		}

		glPopMatrix();
	}
};

#endif

