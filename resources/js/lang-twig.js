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
var keywords = 'block|endblock|do|embed|extends|filter|flush|for|in|from|if|else|endif|elseif|import|include|macro|sandbox|set|spaceless|use|verbatim|as|_self';

PR['registerLangHandler'](
    PR['createSimpleLexer'](
        [],
        [
            [PR['PR_COMMENT'],     /^<\!--[\s\S]*?(?:-\->|$)|^{#[\s\S]*?(?:#})/],
            // twig keywords
            [PR['PR_KEYWORD'],     new RegExp('^(?:' + keywords + ')\\b')],

            [PR['PR_STRING'],      /^(?:\"(?:[^\"\\]|\\[\s\S])*(?:\"|$)|\'(?:[^\'\\]|\\[\s\S])*(?:\'|$))/, null, '"\''],
            // twig syntax
            [PR['PR_TYPE'],        /^(?:\{%|%}|\{\{|}})/ ],
            //[PR['PR_PLAIN'],       /^[^<?]+|[^{?]/],

            [PR['PR_PLAIN'],       /^[\t\n\r \xA0]+/, null, '\t\n\r \xA0'],
            [PR['PR_DECLARATION'], /^<!\w[^>]*(?:>|$)/],
            [PR['PR_PUNCTUATION'], /^(?:<[%?]|[%?]>)/],

            ['lang-',        /^<xmp\b[^>]*>([\s\S]+?)<\/xmp\b[^>]*>/i],
            // Unescaped content in javascript.  (Or possibly vbscript).
            ['lang-js',      /^<script\b[^>]*>([\s\S]*?)(<\/script\b[^>]*>)/i],
            // Contains unescaped stylesheet content
            ['lang-css',     /^<style\b[^>]*>([\s\S]*?)(<\/style\b[^>]*>)/i],
            ['lang-in.tag',  /^(<\/?[a-z][^<>]*>)/i]
        ]),
    ['twig']);