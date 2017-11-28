project(
    'gtk3-hello',
    'c',
    default_options : ['c_std=c99']
)

gtk_dep = dependency('gtk+-3.0')
sources = ['gtk3-hello.c']
executable('gtk3-hello', sources, dependencies: gtk_dep)
