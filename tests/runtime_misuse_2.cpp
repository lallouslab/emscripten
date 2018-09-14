// Copyright 2015 The Emscripten Authors.  All rights reserved.
// Emscripten is available under two separate licenses, the MIT license and the
// University of Illinois/NCSA Open Source License.  Both these licenses can be
// found in the LICENSE file.

#include <stdio.h>
#include <emscripten.h>

extern "C" {

int noted = 0;

char* EMSCRIPTEN_KEEPALIVE note(int n) {
  EM_ASM({ Module.noted = $0 }, (int)&noted);
  EM_ASM({ out([$0, $1]) }, n, noted);
  noted += n;
  EM_ASM({ out(['noted is now', $0]) }, noted);
  return (char*)"silly-string";
}

void free(void*) { // free is valid to call even after the runtime closes, so useful as a hack here for this test
  EM_ASM({ out(['reporting', $0]) }, noted);
}

}

