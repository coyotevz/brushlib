#
# mypaintlib build script
#

import os

brushlib_major_version = 1
brushlib_minor_version = 1

APPNAME = 'mypaint'
VERSION = '.'.join([str(v) for v in [brushlib_major_version,
                                     brushlib_minor_version]])

top = '.'
out = 'build'


def options(opt):
    opt.load('compiler_c')
    opt.add_option('--no-scm', action='store_true', default=False,
                   help='Disable SCM detection [default: No]', dest='no_scm')


def configure(conf):
    conf.check_waf_version(mini='1.8.5')
    conf.load('compiler_c')

    conf.check_cc(lib='m', cflags='-Wall', uselib_store='M')
    conf.check_cfg(package='glib-2.0', uselib_store='GLIB', mandatory=True,
                   args='--cflags --libs')
    conf.check_cfg(package='json-c', uselib_store='JSONC', mandatory=True,
                   args='--cflags --libs')

    revision = get_git_rev(conf)

    conf.define('ENABLE_NLS', 1)
    conf.define('PACKAGE', APPNAME, quote=True)
    conf.define('VERSION', VERSION, quote=True)
    conf.define('REVISION', revision or '-1', quote=True)
    conf.define('GETTEXT_PACKAGE', APPNAME, quote=True)

    conf.define('MYPAINT_TITLE_SIZE', 64)
    conf.define('MYPAINT_MAX_THREADS', 16)
    conf.define('MYPAINT_MAX_MIPMAP_LEVEL', 4)

    conf.write_config_header('mypaint-config.h', guard='MYPAINTCONFIG_H')

    if revision is not None:
        conf.msg('Compiling Git revision', revision)


def build(bld):
    bld(
        features='c cshlib',
        source=bld.path.ant_glob('*.c'),
        target='mypaint',
        includes='.',
        use='GLIB JSONC',
    )


def get_git_rev(conf):
    if conf.options.no_scm:
        return None

    if not os.path.isdir('.git'):
        return None

    try:
        cmd = 'git rev-parse --short --revs-only HEAD'
        revision = conf.cmd_and_log(cmd).strip()
    except WafError as error:
        revision = None

    return revision

# vim:ft=python
