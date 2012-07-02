VERSION='0.0.1'
APPNAME='honeytypes'

top = '.'
out = 'build'

import Logs

def options(opt):
	opt.load('compiler_cxx gtest')

def configure(conf):
	conf.load('compiler_cxx gtest')
	conf.env.append_unique('CXXFLAGS', ['-Wall', '-g', '-march=native', '-O4'])
	conf.env.append_unique('CXXFLAGS', ['-std=gnu++0x'])

def build(bld):
	bld(rule='ruby ${SRC} > ${TGT}', source = 'methods.rb', target='honeytypes/methods.gen.h')
	bld.stlib(
		target = 'honeytypes',
		includes = ['.'],
		source = '''
			stringid.cpp
			int.cpp
			string.cpp
			var.cpp
			'''.split()
		)

	# ptnk_test
	if not bld.env.LIB_GTEST or len(bld.env.LIB_GTEST) == 0:
		Logs.warn('gtest is not found / skipping test')
	else:
		bld.program(
		 	target = 'honeytypes_test',
			features = 'gtest',
		 	use = 'GTEST honeytypes',
			includes = ['.'],
		 	source = '''
			test/stringid_test.cpp
			test/honeytypes_test.cpp
			'''.split()
		 	)
	
	bld.program(
		target = 'bench_stringid',
		use = 'honeytypes',
		lib = 'rt',
		includes = ['.'],
		source = 'test/bench_stringid.cpp'
		)
