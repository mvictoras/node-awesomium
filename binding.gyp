{
	'targets': [{
		'target_name': 'awesomium',
		"sources": [ "src/awesomium.cc", "src/webBrowser.cc" ],
		'default_configuration': 'Release',
		'xcode_settings': {
			'OTHER_CFLAGS': [
				'<!@(pkg-config --cflags awesomium)'
			],
		},
		'cflags': [
			'<!@(pkg-config --cflags awesomium)'
		],
		'ldflags': [
			'<!@(pkg-config --libs awesomium)'
		],
		'libraries': [
			'<!@(pkg-config --libs awesomium)'
		]
	}]
}
