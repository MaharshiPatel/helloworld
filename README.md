# CPP Helloworld Sample Project

## Prerequisite 
- JFrog CLI and `jq` required 
    - [JFrog CLI](https://jfrog.com/getcli/)
    - `jq` - `brew install jq`

## Project Setup
- Clone the project
- cd `HELLOWORLD/`
- Open `helloworld.cpp` and review
- To build executable, RUN `g++ -o helloworld helloworld.cpp`

## For C/C++ Project scan
- RUN `jf rt bp --dry-run=true  {{NAME_OF_BUILD}} 1 > build_info.json`. This will generate Build info and save it as JSON file.
    - For myself, `jf rt bp --dry-run=true  cpp_build 1 > build_info.json`


**NOTE**: Make sure that we added `"modules": []` in your `build_info.json` before run below snippet. 

the following command will :
1. add type=cpp to the module
2. add type=cpp for each dependency
3. update the component id for each dependency 
- RUN
    ```
    jq '.modules[] += {"type":"cpp"}' build_info.json |\
    jq '.modules[].dependencies[] += {"type":"cpp"}' |\
    jq '(.modules[].dependencies[] | select(.id == "poco" ) | .id)    |= "poco:1.9.0.0"' |\
    jq '(.modules[].dependencies[] | select(.id == "poco" ) | .id)    |= "sqlite3:299.1.0.8"' > build_info_xray.json
    ```

- RUN, `jf rt curl -XPUT /api/build -H "Content-Type: application/json" -T build_info_xray.json` This will upload build info. 

**NOTE**: Make sure the build is index under Xray Index Resources. 


![Scan Result](<Screenshot 2023-07-18 at 10.09.30 AM.png>)



References:
- [Document for scanning C/C++ build](https://jfrog.com/help/r/jfrog-artifactory-documentation/conan-and-c/c-support-in-xray)
- Used [this](https://www.dll-files.com/) to find out SHAs


