require_relative 'point'

class Grid
  attr_accessor :data, :ys, :xs

  def initialize()
    @data = Hash.new
    @xs = 0
    @ys = 0
  end

  def <<(line)
    line = line.strip
    line.chars.each_with_index do |c, i|
      @data[Point.new(@ys, i)] = c
    end
    @xs = [@xs, line.length].max
    @ys += 1
  end

  def to_s()
    str = ""
    @ys.times do |y|
      @xs.times do |x|
        str += @data[Point.new(y, x)] || '?'
      end
      str += "\n"
    end
    str
  end

  def method_missing(name, *args, &block)
    @data.send(name, *args, &block)
  end
end
