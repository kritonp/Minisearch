# Minisearch
## Description ##
A simple search engine. Using [Trie](https://en.wikipedia.org/wiki/Trie). Score calculated with [BM25](https://en.wikipedia.org/wiki/Okapi_BM25).<br>
Read & Store a text document to memory and search queries on it.<br>
Example of document file: <br>
0 The quick brown fox leaped over the lazy lazy dog  
1 Quick brown foxes leaped over lazy dogs for fun  
![Img](/TrieTree.PNG)<br>

## Compile & Run ##
```$ make```  
```$ ./minisearch -i input_file.txt -k K```<br> 

## Commands ##
```/search q1 q2 ... q10```  
eg: /search brown lazy  
Output:  
```
( 1) [0.0341] Quick brown foxes leaped over lazy dogs for fun
                    ^^^^^                   ^^^^
( 0) [0.0320] The quick brown fox leaped over the lazy lazy dog
                        ^^^^^                     ^^^^ ^^^^
```
```/df```<br>
Output:  
the 1  
quick 1  
over 2  
leaped 2  
lazy 2  
fun 1  
foxes 1  
fox 1  
for 1  
dogs 1  
dog 1  
brown 2  
The 1  
Quick 1  
```/df word```  
eg: /df leaped<br>
Outuput:<br>
leaped 2<br>
```/tf id_doc word```  
eg: /tf 0 lazy<br>
Outuput: 
0 lazy 2<br>
```/help```<br>
It will print the current options<br>
```/exit```  
Program termination

