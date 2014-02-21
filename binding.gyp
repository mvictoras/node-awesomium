{
	'targets': [{
		'target_name': 'awesomium',
		"sources": [ "src/awesomium.cc", "src/webBrowser.cc" ],
		'default_configuration': 'Release',
        'conditions': [
            ['OS=="win"', 
                {
                    'ldlags': [
                        '-lawesomium',
                    ],
                },
            ],
            ['OS=="mac"',
                {
                    'ldflags': [
                        '-framework Awesomium',
                    ],
                },
            ],
		    ['OS=="win"',
                {
                    'ldflags': [
                        '',
                    ],
                },
            ],
        ]
	}]
}
