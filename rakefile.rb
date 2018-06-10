require(File.join(ENV['gubg'], 'shared'))
include GUBG
require('gubg/build/Executable')
require('gubg/build/Library')

task :default do
    sh "rake -T"
end

task :clean do
    rm_rf '.cache'
end

desc("Prepare: clone SFML and termbox")
task :prepare do
    Dir.chdir(GUBG::mkdir("extern")) do
        git_clone("https://github.com/SFML", "SFML")
        git_clone("https://github.com/ocornut", "imgui")
        git_clone("https://github.com/eliasdaler", "imgui-sfml")
        git_clone('https://github.com/nsf', 'termbox')
    end
    publish('fonts', dst: 'fonts')
    publish('src/imui', dst: 'include/imui', pattern: '**/*.hpp')
    publish('src/tui', dst: 'include/tui', pattern: '**/*.hpp')
    publish('src', pattern: '**/*.hpp', dst: 'include')
end

task :run
