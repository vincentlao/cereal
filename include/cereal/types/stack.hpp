/*
  Copyright (c) 2013, Randolph Voorhies, Shane Grant
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of cereal nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef CEREAL_TYPES_STACK_HPP_
#define CEREAL_TYPES_STACK_HPP_

#include <cereal/cereal.hpp>
#include <stack>

namespace cereal
{
  namespace stack_detail
  {
    //! Allows access to the protected container in stack
    template <class T, class C> inline
    C const & container( std::stack<T, C> const & stack )
    {
      struct H : public std::stack<T, C>
      {
        static C const & get( std::stack<T, C> const & s )
        {
          return s.*(&H::c);
        }
      };

      return H::get( stack );
    }
  }

  //! Saving for std::stack
  template <class Archive, class T, class C> inline
  void save( Archive & ar, std::stack<T, C> const & stack )
  {
    ar( _CEREAL_NVP("container", stack_detail::container( stack )) );
  }

  //! Loading for std::stack
  template <class Archive, class T, class C> inline
  void load( Archive & ar, std::stack<T, C> & stack )
  {
    C container;
    ar( container );
    stack = std::stack<T, C>( std::move( container ) );
  }
} // namespace cereal

#endif // CEREAL_TYPES_STACK_HPP_
