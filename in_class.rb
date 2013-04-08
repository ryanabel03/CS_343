def factors(number)
  (1..number).to_a.select { |num| number % num == 0}
end

def is_prime?(number)
  factors(number).size > 2 ? false : true 
end


def all_factors
  (1..150).to_a.each do |num|
    result = factors(num)
    if is_prime?(num)
      puts "* #{num} #{result.inspect}"
    else
      puts "#{num} #{result.inspect}"
    end
  end
end
