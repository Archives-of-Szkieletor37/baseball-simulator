#!/usr/bin/ruby
#
require 'gimei'


printf(" ")
4000.times do
  gimei = Gimei.male
  printf("%s %s\n", gimei.first.kanji, gimei.first.hiragana)
end
printf("\n")
