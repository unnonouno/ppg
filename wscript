VERSION = '0.1.0'
APPNAME = 'ppg'


def options(ctx):
    ctx.load('compiler_cxx')
    ctx.load('unittest_gtest')


def configure(ctx):
    ctx.load('compiler_cxx')
    ctx.load('unittest_gtest')

    ctx.check_cfg(package='pficommon',
                  args='--cflags --libs',
                  atleast_version='1.3.0')

    ctx.env.CXXFLAGS += ['-W', '-Wall', '-g', '-fopenmp', '-O2']


def build(bld):
    bld.recurse('src')
