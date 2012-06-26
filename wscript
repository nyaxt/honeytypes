VERSION='0.0.1'
APPNAME='ptnk'

top = '.'
out = 'build'

import Logs

def options(opt):
	opt.load('compiler_cxx gtest')

def configure(conf):
	conf.load('compiler_cxx gtest')
	conf.env.append_unique('CXXFLAGS', ['-Wall', '-g', '-march=native'])
	conf.env.append_unique('CXXFLAGS', ['-std=gnu++0x'])

def build(bld):
	bld.program(
		target = 'honeytypes',
		
		source = 'honeytypes.cpp'
		)

	# ptnk_test
	if not bld.env.LIB_GTEST or len(bld.env.LIB_GTEST) == 0:
		Logs.warn('gtest is not found / skipping test')
	else:
		pass
		# bld.program(
		# 	target = 'stageprof_test',
		# 	use = 'TCMALLOC PTHREAD GTEST ptnk',
		# 	source = 'stageprof_test.cpp'
		# 	)
