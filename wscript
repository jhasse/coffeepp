#!/usr/bin/env python

from waflib import Configure
Configure.autoconfig = True

VERSION = '0.2'
APPNAME='coffee++'
top = '.'
out = 'build'

CPP_SOURCES = ['src/file.cpp', 'src/line.cpp', 'src/tokenizer.cpp']

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
	elif sys.platform in ['win32', 'msys']:
		ctx.env.LIB_COFFEEPP = ['boost_program_options-mt.dll']
		ctx.env.LIB_UNIT_TEST = ['boost_unit_test_framework-mt']
	else: # Linux
		ctx.env.LIB_COFFEEPP = ['boost_program_options']
		ctx.env.LIB_UNIT_TEST = ['boost_unit_test_framework']

def build(bld):
	bld.program(features='cxx cxxprogram',
	            source=CPP_SOURCES + ['src/main.cpp'],
	            target = 'coffee++',
	            use = 'COFFEEPP')
	bld.program(features='test',
	            source=CPP_SOURCES + bld.path.ant_glob('unit_test/*.cpp'),
	            target='test',
	            use='COFFEEPP UNIT_TEST')
	from waflib.Tools import waf_unit_test
	bld.add_post_fun(waf_unit_test.summary)
