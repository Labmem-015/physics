__kernel void hello_kernel(__global char* data) {
    // Each thread gets assigned a specific index ID
    int gid = get_global_id(0);
    
    // Define string constants to populate the character array
    char stringToSend[] = "Hello, World!";
    
    // Assign character matching the global ID to the device memory buffer
    data[gid] = stringToSend[gid];
}
