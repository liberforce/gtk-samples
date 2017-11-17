project(
    'gtk3-test',
    'c',
    default_options : ['c_std=c99']
)

gtk_dep = dependency('gtk+-3.0')
sources = ['gtk3-test.c']
executable('gtk3-test', sources, dependencies: gtk_dep)
