file(REMOVE_RECURSE
  "system_server_test"
  "system_server_test.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/system_server_test.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
