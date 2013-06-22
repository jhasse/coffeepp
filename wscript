#!/usr/bin/env python

VERSION = '0.1'
APPNAME='coffee++'
top = '.'
out = '.'

CPP_SOURCES = ['src/file.cpp', 'src/line.cpp']

from waflib.Tools.compiler_cxx import cxx_compiler
cxx_compiler['win32'] = ['g++']
import sys

def options(opt):
	opt.load('compiler_cxx waf_unit_test')

def configure(ctx):
	ctx.load('compiler_cxx waf_unit_test')
	ctx.env.CXXFLAGS = ['-Wall', '-std=c++11', '-g']
	if sys.platform == 'darwin':
		ctx.env.CXX = 'clang'
		ctx.env.append_value('CXXFLAGS', ['-stdlib=libc++'])
		ctx.env.LINKFLAGS = ['-stdlib=libc++']
		ctx.env.LIB_COFFEEPP = ['boost_program_options']
		ctx.env.INCLUDES_COFFEEPP = ['/opt/local/include']
		ctx.env.LIBPATH_COFFEEPP = ['../lib/mac']
	elif sys.platform == 'win32':
		ctx.env.INCLUDES_COFFEEPP = ['../boost-libs/include']
		ctx.env.LIBPATH_COFFEEPP = ['../boost-libs/lib/win']
		ctx.env.LIB_COFFEEPP = ['boost_program_options-mgw47-mt-1_51']
		ctx.env.LIB_UNIT_TEST = ['boost_unit_test_framework-mgw47-mt-1_51']
	else: # Linux
		ctx.env.LIB_COFFEEPP = ['boost_program_options']

def build(bld):
	bld.program(features='cxx cxxprogram',
	            source=CPP_SOURCES + ['src/main.cpp'],
	            target = 'coffee++',
	            use = 'COFFEEPP')
	bld.program(features='test',
	            source=CPP_SOURCES + ['unit_test/comments.cpp'],
	            target='unit_test/unit_test',
	            use='COFFEEPP UNIT_TEST')
	from waflib.Tools import waf_unit_test
	bld.add_post_fun(waf_unit_test.summary)