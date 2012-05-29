#version 330
#ifndef ATTRIBUTES_INCLUDED
#define ATTRIBUTES_INCLUDED

#extension GL_ARB_separate_shader_objects : enable

layout(location=0) in vec4 aPositionOs;
layout(location=1) in vec4 aNormalOs;
layout(location=2) in vec4 aTexCoord0Os;
layout(location=3) in vec4 aTexCoord1Os;
layout(location=4) in vec4 aTexCoord2Os;
layout(location=5) in vec4 aTexCoord3Os;
layout(location=6) in vec4 aTexCoord4Os;
layout(location=7) in vec4 aTexCoord5Os;
layout(location=8) in vec4 aTangentOs;
layout(location=9) in vec4 aBitangentOs;

#endif