// ======================================================================== //
// Copyright 2009-2013 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#ifndef __EMBREE_BVH4_INTERSECTOR8_HYBRID_H__
#define __EMBREE_BVH4_INTERSECTOR8_HYBRID_H__

#include "bvh4.h"
#include "../include/intersector8.h"

namespace embree
{
  /*! BVH4 Traverser. Packet traversal implementation for a Quad BVH. */
  template<typename TriangleIntersector8, typename TriangleIntersector1>
    class BVH4Intersector8Hybrid : public Intersector8
  {
    /* shortcuts for frequently used types */
    typedef typename TriangleIntersector8::Triangle Triangle;
    typedef typename BVH4::NodeRef NodeRef;
    typedef typename BVH4::Node Node;

  public:
    BVH4Intersector8Hybrid (const BVH4* bvh) 
      : Intersector8((intersectFunc)intersect,(occludedFunc)occluded), bvh(bvh) {}

    static Intersector8* create(const Accel* bvh) { 
      return new BVH4Intersector8Hybrid((const BVH4*)bvh); 
    }

    static void   intersect(const BVH4Intersector8Hybrid* This, Ray8& ray, const __m256 valid);
    static __m256 occluded (const BVH4Intersector8Hybrid* This, Ray8& ray, const __m256 valid);

  private:
    const BVH4* bvh;
  };
}

#endif
