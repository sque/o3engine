#ifndef O3ENGINE_OPENGL2_SUPPORT_HPP_INCLUDED
#define O3ENGINE_OPENGL2_SUPPORT_HPP_INCLUDED

#include "./base_prereqs.hpp"
#include "./vector2.hpp"
#include "./vector3.hpp"
#include "./vector4.hpp"
#include "./triangle3.hpp"
#include "./angle.hpp"
#include "./color.hpp"

// System Detection
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#endif

namespace o3engine
{
    /**
     @defgroup gl_support OpenGL compatibility layer
     This module provides overloaded functions of OpenGL SDK
     that get as arguments o3engine's data types.
     @{
     */

    //! @name Convert a value to an array of GLfloats
    //! @{
    inline GLfloat * toGLfloat3V(const Color & c, GLfloat * p3V)
    {   p3V[0] = c.red; p3V[1] = c.green; p3V[2] = c.blue; return p3V;   }

    inline GLfloat * toGLfloat4V(const Color & c, GLfloat * p4V)
    {   p4V[0] = c.red;
        p4V[1] = c.green;
        p4V[2] = c.blue;
        p4V[3] = c.alpha;
        return p4V;
    }

    //! @}

    //! @name glTranslate functions
    //! @{
    inline void glTranslate(const Vector2 & r, Real z = 0)
    {   ::glTranslatef((GLfloat)r.x, (GLfloat)r.y, z);    }

    inline void glTranslate(const Vector3 & r)
    {   ::glTranslatef((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z);    }
    //! @}


    //! @name glRotate functions
    //! @{
    inline void glRotate(const Vector4 & r)
    {   //if (r.getW() != 0)
        ::glRotatef((GLfloat)r.w, (GLfloat) r.x,(GLfloat) r.y,(GLfloat) r.z);
    }

    inline void glRotate(const Vector3 & r, const Angle & _a)
    {   ::glRotatef((GLfloat)_a.getDegrees(), (GLfloat) r.x,(GLfloat) r.y,(GLfloat) r.z);    }


    inline void glRotate(const Quaternion & q)
    {   Angle _angle; Vector3 _axis;
        q.toAxisAngle(_axis, _angle);
        glRotate(_axis, _angle);
    }
    //! @}


    //! @name glScale functions
    //! @{
    inline void glScale(const Vector3 & r)
    {   ::glScalef((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z); }

    inline void glScale(const Vector2 & r, Real z = 1)
    {   ::glScalef((GLfloat)r.x, (GLfloat)r.y, (GLfloat)z);   }
    //! @}


    //! @name glVertex functions
    //! @{
    inline void glVertex(const Vector2 & r)
    {   ::glVertex2f((GLfloat)r.x, (GLfloat)r.y);  }

    inline void glVertex(const Vector3 & r)
    {   ::glVertex3f((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z); }

    inline void glVertex(const Vector4 & r)
    {   ::glVertex4f((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z, (GLfloat)r.w); }

    inline void glVertex(const Triangle3 & tri3)
    {   glVertex(tri3.point_a);   glVertex(tri3.point_b);   glVertex(tri3.point_c);   }
    //! @}

    //! @name glNormal functions
    //! @{
    inline void glNormal(const Vector3 & r)
    {   ::glNormal3f((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z); }
    //! @}

    //! @name glTexCoord functions
    //! @{
    inline void glTexCoord(const Vector2 & r)
    {   ::glTexCoord2d((GLfloat)r.x, (GLfloat)r.y);   }

    inline void glTexCoord(const Vector3 & r)
    {   ::glTexCoord3d((GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z ); }
    //! @}

    //! @name glLight functions
    //! @{
    inline void glLight(GLenum light, GLenum pname, const Vector4 & r)
    {   GLfloat tmp_vector[4] =
            {(GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z, (GLfloat)r.w};
        ::glLightfv(light, pname, tmp_vector);
    }

    inline void glLight(GLenum light, GLenum pname, const Vector3 & r, Real w = 0)
    {   GLfloat tmp_vector[4] =
            {(GLfloat)r.x, (GLfloat)r.y, (GLfloat)r.z, (GLfloat)w};
        ::glLightfv(light, pname, tmp_vector);
    }

    inline void glLight(GLenum light, GLenum pname, const Color & col)
    {   GLfloat tmp_vector[4] =
            {(GLfloat)col.red, (GLfloat)col.green, (GLfloat)col.blue, (GLfloat)col.alpha};
        ::glLightfv(light, pname, tmp_vector);
    }

    inline void glLightModel(GLenum pname, const Color & col)
    {   GLfloat tmp_color[4] =
            {(GLfloat)col.red, (GLfloat)col.green, (GLfloat)col.blue, (GLfloat)col.alpha};
        ::glLightModelfv(pname, tmp_color);
    }

    //! @}

    //! @name glColor functions
    //! @{
    inline void glColor3(const Color  & c)
    {   ::glColor3f((GLfloat) c.red, (GLfloat) c.green, (GLfloat) c.blue);    }

    inline void glColor4(const Color  & c)
    {   ::glColor4f((GLfloat) c.red, (GLfloat) c.green, (GLfloat) c.blue, (GLfloat)c.alpha);    }
    //! @}

    //! @name glClearXXXXX functions
    //! @{
    inline void glClearColor(const Color &c)
    {   ::glClearColor((GLfloat) c.red, (GLfloat) c.green, (GLfloat) c.blue, (GLfloat)c.alpha);    }

    inline void glClearAccum(const Color &c)
    {   ::glClearAccum((GLfloat) c.red, (GLfloat) c.green, (GLfloat) c.blue, (GLfloat)c.alpha);    }
    //! @}

    //! @}
}

#endif
