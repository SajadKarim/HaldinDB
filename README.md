![C++ CI](https://github.com/SajadKarim/haldendb/actions/workflows/msbuild.yml/badge.svg)
![C++ CI](https://github.com/SajadKarim/haldendb/actions/workflows/cmake-multi-platform.yml/badge.svg)

Note: Use branch "feature/sctp_I_v11"

# Project

This C++ project is an ongoing effort to explore and implement various B<sup>$\epsilon$</sup>-Tree and B<sup>+</sup>-Tree variants. Designed as a resource for both educational and practical applications, it aims to provide insights into the different optimizations and uses of B<sup>$\epsilon$</sup>-Tree and B<sup>+</sup>-Tree in databases and filesystems. As work progresses, the project will feature implementations ranging from basic structures suitable for learning purposes to more advanced versions optimized for specific challenges such as concurrency and cache efficiency. Contributors are welcome to join in this evolving exploration of one of the most fundamental data structures in computer science.

The project currently includes the following modules:
- **libcache**: A library for managing cache operations, including LRUCache.
- **libbtree**: The main library for implementing various B<sup>$\epsilon$</sup>-Tree and B<sup>+</sup>-Tree variants.
- **sandbox**: A utility for debugging and validating functionality.
- **test_all**: A unit testing suite.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them, for example, Visual Studio, any specific editions or versions, etc.

1. **Windows**
   
   1.1. [Visual Studio](https://visualstudio.microsoft.com/downloads/) 2022 or later
   
   1.2. C++ development tools for Visual Studio

2. **Linux**

   2.1. CMake
   
   2.2 g++-11

   2.2. glog

   2.5. libpmem (when using NVRAM)
  
### Installing

A step by step series of examples that tell you how to get a development environment running.

1. **Clone the repository**

   ```bash
   git clone https https://github.com/SajadKarim/haldendb.git
   cd haldendb
   git checkout feature/sctp
   
2. **Windows**
   
   2.1. Open the Solution
   
   Open haldendb.sln with Visual Studio.

   2.2. Build the Project

   Navigate to Build > Build Solution or press Ctrl+Shift+B to build the project.

   2.3. Run the Application

   Set the desired project as the startup project by right-clicking on the project in the Solution Explorer and selecting Set as StartUp Project.
   Run the project by clicking on Debug > Start Without Debugging or pressing Ctrl+F5.

4. **Linux**
   
   4.1. cd test_all

   4.2. mkdir build

   4.3. cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-D__CONCURRENT__ -D__TREE_WITH_CACHE__"

   4.4. cmake --build .

   4.5. ./test_all

   

> The Markhor/Ibex (Halden in Burushaski), a majestic wild goat species native to the mountainous regions of Central Asia, is renowned for its distinctive corkscrew horns and impressive agility in rugged terrains. It faces predation challenges from formidable carnivores such as snow leopards, wolves, Eurasian lynx, and brown bears. The golden eagle has been reported to prey upon young markhor. To survive in these harsh environments, Markhors and Ibexes have developed remarkable adaptations. Their keen senses, including exceptional eyesight and acute hearing, help them detect approaching predators from a distance. Additionally, their powerful climbing abilities allow them to navigate steep and rocky terrain, providing escape routes from potential threats. These ungulates also exhibit a strong herding behavior, with individuals collectively vigilant against predators. The combination of physical prowess, keen senses, and social structures enhances their chances of survival in the challenging ecosystems they call home.

----

# License

## Apache License, Version 2.0

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

### Attribution

You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.

- Attribution: [Sajad Karim], [[https://github.com/SajadKarim/blog/](https://github.com/SajadKarim/haldendb)]

## MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

### Additional Requirement

You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.

- Attribution: [Sajad Karim], [[https://github.com/SajadKarim/blog/](https://github.com/SajadKarim/haldendb)]

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
