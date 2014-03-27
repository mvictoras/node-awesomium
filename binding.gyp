{
	'targets': [{
		'target_name': 'awesomium',
        'variables': {
            'WIN_LIBJPEG_ROOT%': 'C:\\libjpeg-turbo\\lib\\',
        },
		'default_configuration': 'Release',
        'conditions': [
            ['OS=="linux"', 
                {
		           'sources': [ 'src/awesomium.cc', 'src/webBrowser.cc', 'src/cefHandler.cc' ],
                   'include_dirs': [
                        '$(CEF3_DIR)',
                    ],
                    'defines': [
                        'USING_CEF_SHARED'
                    ],
                    'cflags_cc': [
                        '<!@(pkg-config --cflags gtk+-2.0)',
                    ],
                    'ldflags': [
                        '<!@(pkg-config --libs-only-L --libs-only-other gtk+-2.0 gthread-2.0)',
                        '-Wl,-rpath,\'$$ORIGIN/../../deps/cef3/\''
                    ],
                    'libraries': [
                        '-ljpeg',
                        '<!@(pkg-config --libs-only-l gtk+-2.0 gthread-2.0)',
                        '-L<(module_root_dir)/deps/cef3',
                        '-lcef',
                        '<(module_root_dir)/deps/cef3/libcef_dll_wrapper.a',
                    ],
                    'cflags': [
                        '-fopenmp'
                    ],
                },
            ],
            ['OS=="mac"',
                {
                    'ldflags': [
                        '-framework Awesomium',
                        '-lawesomium',
                    ],
                },
            ],
		    ['OS=="win"',
                {
                    'link_settings': {
                        'libraries': [
                            '-l<(WIN_LIBJPEG_ROOT)turbojpeg-static.lib',
                            '-l$(AWE_DIR)build\\lib\\awesomium.lib'
                        ],
                    },
                    'include_dirs': [
                      '$(AWE_DIR)include',
                      'C:\\libjpeg-turbo\\include',
                      ],
                },
            ],
        ]
	}]
}
