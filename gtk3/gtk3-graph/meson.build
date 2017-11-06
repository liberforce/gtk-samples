project('gtk3-graph', 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

gtk_dep = dependency('gtk+-3.0')
sources = ['gtk3-graph.c']

executable('gtk3-graph', sources, dependencies: [gtk_dep, m_dep])
