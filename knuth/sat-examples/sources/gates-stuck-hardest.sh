#!/bin/sh
# one argument, a random seed

echo "1W21#10"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 1W21#10 | sat13 h9 s$1 > /dev/null
echo "0W21#18"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0W21#18 | sat13 h9 s$1 > /dev/null
echo "1W21#19"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 1W21#19 | sat13 h9 s$1 > /dev/null
echo "0D29:8#16"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D290816 | sat13 h9 s$1 > /dev/null
echo "0D34:13#3"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D341303 | sat13 h9 s$1 > /dev/null
echo "0D34:13#8"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D341308 | sat13 h9 s$1 > /dev/null
echo "0D34:13#9"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D341309 | sat13 h9 s$1 > /dev/null
echo "0B41:41"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0B41:41 | sat13 h9 s$1 > /dev/null
echo "0D42:3#3"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D42:3#3 | sat13 h9 s$1 > /dev/null
echo "0D42:3#7"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D42:3#7 | sat13 h9 s$1 > /dev/null
echo "0D42:3#8"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D42:3#8 | sat13 h9 s$1 > /dev/null
echo "0D42:13#2"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D421302 | sat13 h9 s$1 > /dev/null
echo "0B42:42"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0B42:42 | sat13 h9 s$1 > /dev/null
echo "0D43:9#2"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D43:9#2 | sat13 h9 s$1 > /dev/null
echo "0B43:43"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0B43:43 | sat13 h9 s$1 > /dev/null
echo "0D44:10#2"
sat-gates-stuck-namekludge /tmp/prod,16,32-wires.gb 0D441002 | sat13 h9 s$1 > /dev/null
