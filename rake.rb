require("gubg/shared")

here = File.dirname(__FILE__)

namespace :ui do
	task :prepare do
		Dir.chdir(Gubg.mkdir(here, "extern")) do
			Gubg.git_clone("https://github.com/SFML", "SFML")
			Gubg.git_clone("https://github.com/ocornut", "imgui")
			Gubg.git_clone("https://github.com/eliasdaler", "imgui-sfml")
			Gubg.git_clone('https://github.com/nsf', 'termbox')
		end
		Gubg.publish(here, 'fonts', dst: 'fonts')
		Gubg.publish(here, 'src/imui', dst: 'include/imui', pattern: '**/*.hpp')
		Gubg.publish(here, 'src/tui', dst: 'include/tui', pattern: '**/*.hpp')
		Gubg.publish(here, 'src', pattern: '**/*.hpp', dst: 'include')
	end
end