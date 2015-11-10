require(File.join(ENV['gubg'], 'shared'))
include GUBG
require('gubg/build/Executable')

task :default => :help
task :help do
    puts("The following tasks can be specified:")
    puts("* declare: SFML and local headers")
    puts("* define:")
end

task :declare do
    Dir.chdir(shared_dir('extern')) do
        git_clone('https://github.com/SFML', 'SFML') do
            if !File.exist?('build')
                Dir.mkdir('trybuild')
                Dir.chdir('trybuild') do
                    #For ubuntu, these packages should be installed:
                    #sudo apt-get install freeglut3
                    #sudo apt-get install freeglut3-dev
                    #sudo apt-get install libxcb-image0
                    #sudo apt-get install libxcb-image0-dev
                    #sudo apt-get install libudev-dev
                    #sudo apt-get install libjpeg-dev
                    #sudo apt-get install libopenal-dev
                    #sudo apt-get install libvorbis-dev
                    #sudo apt-get install libflac-dev
                    sh 'cmake ..'
                    sh 'make -j 4'
                end
                mv('trybuild', 'build')
            end
            publish('build/lib', '*.so', dst: 'lib')
            publish('include', '**/*', dst: 'include')
        end
    end
end

task :define => :declare do
    exe = Build::Executable.new('test.exe')
    exe.add_sources('src/test/test.cpp')
    exe.add_library_path(shared_dir('lib'))
    exe.add_library('sfml-system', 'sfml-window', 'sfml-graphics')
    exe.run
end
