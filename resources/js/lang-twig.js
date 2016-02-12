// Copyright (C) 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// twig tags
var keywords = 'block|endblock|do|embed|extends|filter|flush|for|in|from|if|else|endif|elseif|import|include|macro|sandbox|set|spaceless|use|verbatim';

PR['registerLangHandler'](
    PR['createSimpleLexer'](
        [
        ],
        [
         // block comments are delimited by /* and */
         // single-line comments begin with // and extend to the end of a line
         [PR['PR_COMMENT'],     /^(?:<!--[\s\S]*?-->|{#[\s\S]#})/],

         // a double or single quoted, possibly multi-line, string
         [PR['PR_STRING'],      /^(?:\"(?:[^\"\\]|\\[\s\S])*(?:\"|$)|\'(?:[^\'\\]|\\[\s\S])*(?:\'|$))/, null, '"\''],

         // PHP keywords
         [PR['PR_KEYWORD'],     new RegExp('^(?:' + keywords + '|[\S]\(\))\\b')],

         // constants
         [PR['PR_TYPE'],        /^(?:\{%|%}|\{\{|}})/ ],

         // literals, e.g. 1, null, true
         [PR['PR_LITERAL'],     /^(?:true|false|null|this|<[^>]+>)|\d+\b/i],


         // whitespace is made up of spaces, tabs and newline characters.
         [PR['PR_PLAIN'],       /^[\t\n\r \xA0]+/, null, '\t\n\r \xA0'],

         // printable non-space non-special characters
         [PR['PR_PUNCTUATION'], /^(?:[^\t\n\r\$ \xA0\"\'\w]+)/]

        ]),
    ['twig']);