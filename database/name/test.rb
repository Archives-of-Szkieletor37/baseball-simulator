#!/usr/bin/ruby
#
require 'gimei'


printf(" ")
1000.times do
  gimei = Gimei.male
  printf("%s %s\n", gimei.last.kanji, gimei.last.hiragana)
end
printf("\n")
