#
# brushlib build script
#

import os

brushlib_major_version = 1
brushlib_minor_version = 1
brushlib_micro_version = '0'

APPNAME = 'brushlib'
GI_NAMESPACE = 'BrushLib'
VERSION = '.'.join([str(v) for v in [brushlib_major_version,
                                     brushlib_minor_version,
                                     brushlib_micro_version]])

brushlib_api_version = '.'.join([str(v) for v in [brushlib_major_version,
                                                  brushlib_minor_version]])

top = '.'
out = 'build'


def options(opt):
    opt.load('compiler_c')
    opt.add_option('--no-scm', action='store_true', dest='no_scm',
                   help='Disable SCM detection [default: No]')
    opt.add_option('--no-nls', action='store_true', dest='no_nls',
                   help='Disable i18n (native language support)')
    opt.add_option('--no-gir', action='store_true', dest='no_gir',
                   help='Disable Build GObject instrospection data')


def configure(conf):
    conf.check_waf_version(mini='1.8.5')
    conf.load('compiler_c')

    # share data with other contexts
    conf.env.APPNAME = APPNAME
    conf.env.GI_NAMESPACE = GI_NAMESPACE
    conf.env.VERSION = VERSION
    conf.env.API_VERSION = brushlib_api_version

    conf.check_cc(lib='m', cflags='-Wall', uselib_store='M')
    conf.check_cfg(package='glib-2.0', uselib_store='GLIB', mandatory=True,
                   args='--cflags --libs')
    conf.check_cfg(package='gobject-2.0', uselib_store='GOBJECT', mandatory=True,
                   args='--cflags --libs')
    conf.check_cfg(package='json-c', uselib_store='JSONC', mandatory=True,
                   args='--cflags --libs')

    revision = get_git_rev(conf)

    if not conf.options.no_nls:
        conf.define('ENABLE_NLS', 1)
        conf.define('GETTEXT_PACKAGE', APPNAME.lower(), quote=True)

    if not conf.options.no_gir:
        conf.find_program('g-ir-scanner', var='GI_SCANNER')
        conf.find_program('g-ir-compiler', var='GI_COMPILER')

    conf.define('VERSION', VERSION, quote=True)
    conf.define('REVISION', revision or '-1', quote=True)
    conf.define('PACKAGE', APPNAME.lower(), quote=True)

    conf.define('BRUSHLIB_TITLE_SIZE', 64)
    conf.define('BRUSHLIB_MAX_THREADS', 16)
    conf.define('BRUSHLIB_MAX_MIPMAP_LEVEL', 4)

    conf.env.append_value('CFLAGS', '-DHAVE_CONFIG_H')
    conf.env.append_value('CFLAGS', '-DBRUSHLIB_COMPILATION')

    conf.write_config_header('config.h',
                             guard='__BRUSHLIB_CONFIG_H__')

    conf.env['subst_dict'] = {
        "prefix": conf.env["PREFIX"],
        "BRUSHLIB_MAJOR_VERSION": brushlib_major_version,
        "BRUSHLIB_MINOR_VERSION": brushlib_minor_version,
        "BRUSHLIB_MICRO_VERSION": brushlib_micro_version,
        "BRUSHLIB_VERSION": VERSION,
        "BRUSHLIB_REQUIRES": "glib-2.0 >= 2.12 gobject-2.0",
        "VERSION": VERSION,
    }

    conf.env["BRUSHLIB_INCLUDE_PATH"] = "include/brushlib-%s" % brushlib_api_version
    conf.env["BRUSHLIB_HEADERS_PATH"] = "include/brushlib-%s/brushlib" % brushlib_api_version

    if revision is not None:
        conf.msg('Compiling Git revision', revision)


def build(bld):
    bld.recurse('brushlib')


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
