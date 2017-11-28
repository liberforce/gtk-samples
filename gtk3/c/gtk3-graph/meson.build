project(
    'gtk3-graph',
    'c',
    default_options : ['c_std=c99']
)

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

gtk_dep = dependency('gtk+-3.0')
sources = ['gtk3-graph.c']
executable('gtk3-graph', sources, dependencies: [gtk_dep, m_dep])
