{
	'targets': [{
		'target_name': 'awesomium',
        'variables': {
            'WIN_LIBJPEG_ROOT%': 'C:\\libjpeg-turbo\\lib\\'
        },
		'default_configuration': 'Release',
        'conditions': [
            ['OS=="linux"', 
                {
		           'sources': [ 'src/awesomium.cc', 'src/webBrowser.cc' ],
                    'libraries': [
                        '-lawesomium-1-7',
                        '-ljpeg',
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
