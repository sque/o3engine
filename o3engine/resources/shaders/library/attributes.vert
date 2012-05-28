#version 330
#ifndef ATTRIBUTES_INCLUDED
#define ATTRIBUTES_INCLUDED

#extension GL_ARB_separate_shader_objects : enable

layout(location=0) in vec4 aPositionOs;
layout(location=1) in vec4 aNormalOs;
layout(location=2) in vec4 aTexCoord0Os;

#endif