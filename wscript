#!/usr/bin/env python

VERSION = '0.1'
APPNAME='coffee++'
top = '.'
out = 'build'

CPP_SOURCES = ['src/main.cpp', 'src/file.cpp', 'src/line.cpp']

from waflib.Tools.compiler_cxx import cxx_compiler
import sys

def options(opt):
	opt.load('compiler_cxx')

def configure(ctx):
	ctx.load('compiler_cxx')
	ctx.env.CXXFLAGS = ['-Wall', '-std=c++11', '-g']
	if sys.platform == 'darwin':
		ctx.env.CXX = 'clang'
		ctx.env.append_value('CXXFLAGS', ['-stdlib=libc++'])
		ctx.env.LINKFLAGS = ['-stdlib=libc++']
		ctx.env.LIB_COFFEEPP = ['boost_program_options']
		ctx.env.INCLUDES_COFFEEPP = ['/opt/local/include']
		ctx.env.LIBPATH_COFFEEPP = ['../lib/mac']

def build(bld):
	bld.program(features = 'cxx cxxprogram', source=CPP_SOURCES, target = 'coffee++', use = 'COFFEEPP')