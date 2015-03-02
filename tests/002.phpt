--TEST--
Test bitset_init function 
--SKIPIF--
<?php if (!extension_loaded("bitset")) print "skip"; ?>
--FILE--
<?php 
error_reporting(E_ALL ^ E_DEPRECATED);
$test_size = pow(2,8);
if(bitset_init($test_size)){
    echo "bitset init - ok\n";
}

if(bit_set(1)){
    echo "bit_set the 2nd position is set 1\n";
}

if(bit_set(7)){
    echo "bit_set the 8 position is set 1\n";
}

if(bit_unset(1)){
    echo "bit_unset the 2nd position is set 0\n";
}

if(bit_isset(7)){
    echo "bit_isset the 2nd position is set 1\n";
}
?>
--EXPECT--
bitset init - ok
bit_set the 2nd position is set 1
bit_set the 8 position is set 1
bit_unset the 2nd position is set 0
bit_isset the 2nd position is set 1
