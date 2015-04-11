VERSION = '0.1.0'
APPNAME = 'ppg'


def options(ctx):
    ctx.load('compiler_cxx')
    ctx.load('unittest_gtest')

    ctx.add_option('--enable-gcov',
                   action='store_true',
                   default=False,
                   dest='gcov',
                   help='only for debug')


def configure(ctx):
    ctx.load('compiler_cxx')
    ctx.load('unittest_gtest')

    ctx.check_cfg(package='pficommon',
                  args='--cflags --libs',
                  atleast_version='1.3.0')

    ctx.env.CXXFLAGS += ['-W', '-Wall', '-g', '-O2']

    if ctx.options.gcov:
        ctx.env.append_value('CXXFLAGS', '-fprofile-arcs')
        ctx.env.append_value('CXXFLAGS', '-ftest-coverage')
        # ctx.env.append_value('LINKFLAGS', '-lgcov')
        ctx.env.append_value('LINKFLAGS', '-fprofile-arcs')
        ctx.env.append_value('LINKFLAGS', '-ftest-coverage')


def build(bld):
    bld.recurse('src')


def cpplint(ctx):
    filters = [
        '-runtime/references',
        '-build/include_order',
        '-readability/streams',
        '-legal/copyright',
    ]
    cpplint_args = '--filter=%s --extensions=cpp,hpp' % ','.join(filters)

    src_dir = ctx.path.find_node('src')
    files = []
    for f in src_dir.ant_glob('*.cpp *.hpp'):
        files.append(f.path_from(ctx.path))

    args = 'cpplint.py %s %s 2>&1 | grep -v "^\(Done\|Total\)"' % \
           (cpplint_args, ' '.join(files))
    result = ctx.exec_command(args)
    if result == 0:
        ctx.fatal('cpplint failed')


def gcovr(ctx):
    excludes = [
        '.*\\.unittest-gtest.*',
        '.*_test\\.cpp',
    ]

    args = 'gcovr --branches -r . '
    for e in excludes:
        args += ' -e "%s"' % e

    ctx.exec_command(args)
