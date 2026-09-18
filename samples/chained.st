for(auto i = 0u32; i < 4u32; i++){
  print(i);
}
//print(i);

print("----------------");

var x#i32 = 0;
for(x = 0; x < 4; x++){
  print(x);
}

print("----------------");
print(x); // 4
print(`Isso é x: ${x}$`);