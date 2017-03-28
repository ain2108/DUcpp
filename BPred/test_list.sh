echo "1-BIT counter" >> data.sh
echo "BUDGET: 1 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 2 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 4 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 8 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 16 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 32 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 5 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 64 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 5 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 6 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 128 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 7 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 5 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 6 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 7 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 256 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 8 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 7 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 5 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 6 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 7 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 8 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 512 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 0 -k 9 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 1 -k 8 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 2 -k 7 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 3 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 4 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 5 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 6 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 7 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 8 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 1 -m 9 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "2-BIT counter" >> data.sh
echo "BUDGET: 2 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 4 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 8 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 16 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 32 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 4 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 64 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 4 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 5 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 128 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 4 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 5 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 6 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 256 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 7 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 4 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 5 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 6 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 7 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
echo "BUDGET: 512 BITS" >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 0 -k 8 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 1 -k 7 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 2 -k 6 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 3 -k 5 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 4 -k 4 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 5 -k 3 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 6 -k 2 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 7 -k 1 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
$PIN_ROOT/pin -t obj-intel64/bpred.so -n 2 -m 8 -k 0 -o test.out -- convert wallpaper-color-19.jpg -resize 200x200 wallpaper-color-19-reduced.jpg >> data.sh
