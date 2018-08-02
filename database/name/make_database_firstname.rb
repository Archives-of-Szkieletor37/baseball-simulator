#!/usr/bin/ruby
#
require 'gimei'


printf("{")
10000.times do
  gimei = Gimei.male
  printf("{\"%s\", \"%s\"},\n",gimei.first.kanji, gimei.first.hiragana)
end
printf("}\n")
