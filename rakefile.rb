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
end

task :define => :declare do
    exe = Build::Executable.new('test.exe')
    exe.add_sources('src/test/test.cpp')
    exe.add_library('sfml-system', 'sfml-window', 'sfml-graphics')
    exe.run
end

