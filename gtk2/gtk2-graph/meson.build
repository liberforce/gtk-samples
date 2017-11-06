project('gtk2-graph', 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

gtk_dep = dependency('gtk+-2.0')
sources = ['gtk2-graph.c']

executable('gtk2-graph', sources, dependencies: [gtk_dep, m_dep])
