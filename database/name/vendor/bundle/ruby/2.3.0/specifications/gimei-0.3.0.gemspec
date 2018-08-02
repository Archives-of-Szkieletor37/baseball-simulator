# -*- encoding: utf-8 -*-
# stub: gimei 0.3.0 ruby lib

Gem::Specification.new do |s|
  s.name = "gimei"
  s.version = "0.3.0"

  s.required_rubygems_version = Gem::Requirement.new(">= 0") if s.respond_to? :required_rubygems_version=
  s.require_paths = ["lib"]
  s.authors = ["willnet"]
  s.date = "2017-09-28"
  s.description = "random Japanese name and address generator"
  s.email = ["netwillnet@gmail.com"]
  s.homepage = "https://github.com/willnet/gimei"
  s.licenses = ["MIT"]
  s.rubygems_version = "2.5.2.1"
  s.summary = "random Japanese name and address generator. support kanji, hiragana, and katakana"

  s.installed_by_version = "2.5.2.1" if s.respond_to? :installed_by_version

  if s.respond_to? :specification_version then
    s.specification_version = 4

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_runtime_dependency(%q<romaji>, [">= 0"])
      s.add_development_dependency(%q<rake>, [">= 0"])
      s.add_development_dependency(%q<moji>, [">= 0"])
      s.add_development_dependency(%q<minitest>, [">= 0"])
      s.add_development_dependency(%q<coveralls>, [">= 0"])
    else
      s.add_dependency(%q<romaji>, [">= 0"])
      s.add_dependency(%q<rake>, [">= 0"])
      s.add_dependency(%q<moji>, [">= 0"])
      s.add_dependency(%q<minitest>, [">= 0"])
      s.add_dependency(%q<coveralls>, [">= 0"])
    end
  else
    s.add_dependency(%q<romaji>, [">= 0"])
    s.add_dependency(%q<rake>, [">= 0"])
    s.add_dependency(%q<moji>, [">= 0"])
    s.add_dependency(%q<minitest>, [">= 0"])
    s.add_dependency(%q<coveralls>, [">= 0"])
  end
end
