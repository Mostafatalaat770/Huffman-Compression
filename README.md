# **Huffman Compression**

# About

Huffman Algorithm is an efficient way for file Compression and Decompression.
This program exactly follows huffman algorithm. It reads frequent characters from input file and replace it with shorter binary codeword.
The original file can be produced again without loosing any bit.

# Usage

Enter the filename then choose the prefered mode.

# File Structure

<table>
<tr> <td> p (1 byte)          </td><td> p times 0's (p bits)                     </td> </tr>
<tr> <td> Character[1 byte]   </td><td>  Binary codeword String Form[MAX bytes]  </td> </tr>
<tr> <td> Character[1 byte]   </td><td>  Binary codeword String Form[MAX bytes]  </td> </tr>
<tr> <td colspan="2">              :                                        </td> </tr>
<tr> <td colspan="2">              :                                        </td> </tr>
<tr> <td> Character[1 byte]   </td><td>  Binary codeword String Form[MAX bytes]  </td> </tr>
<tr> <td> Character[1 byte]   </td><td>  Binary codeword String Form[MAX bytes]  </td> </tr>
<tr><td>**</td><td>end of huffman codes block</td></tr>

<tr> <td colspan="2">  DATA                                                      </td> </tr>
</table>

p = Padding done to ensure file fits in whole number of bytes. eg, file of 4 bytes + 3 bits must ne padded by 5 bits to make it 5 bytes.

## Example

| Content | Comment                               |
| ------- | ------------------------------------- |
| 4       | Padding count                         |
| b "11"  | character and corresponding code "11" |
| a "0"   | character and corresponding code "0"  |
| c "10"  | character and corresponding code "10" |
| \*\*    | end of huffman code block             |
| ;0      | compressed data                       |

# Algorithm

## Compression:

1. Reads the file to count the frequency of every character used.
2. Forms Huffman tree unique to this file.
3. Uses the Huffman tree to turn every character to its associated
   binary code.
4. Checks if the new string is divisible by 8, if not adds padding
   (zeros) until it is.
5. Combines every 8 bits to form one compressed character.
6. Writes the Huffman tree, padding and compressed text back to the
   file.

## Decompression:

1. Reads the padding, Huffman tree and the compressed text to the
   memory.
2. Changes back every compressed character to 8 bits.
3. Changers the bits back to characters from the Huffman tree.
4. Writes the decompressed text back to the file.

# Contributing

Please feel free to submit issues and pull requests. I appreciate bug reports.
Testing on different platforms is especially appreciated. I only tested on Linux.

# License

This software is in the _Public Domain_. That means you can do whatever you like
with it. That includes being used in proprietary products without attribution or
restrictions. There are no warranties and there may be bugs.

Formally we are using CC0 - a Creative Commons license to place this work in the
public domain. A copy of CC0 is in the LICENSE file.

    "CC0 is a public domain dedication from Creative Commons. A work released
    under CC0 is dedicated to the public domain to the fullest extent permitted
    by law. If that is not possible for any reason, CC0 also provides a lax,
    permissive license as a fallback. Both public domain works and the lax
    license provided by CC0 are compatible with the GNU GPL."
      - http://www.gnu.org/licenses/license-list.html#CC0

# Authros

- **Mostafa Talaat** - [mostafatalaat770](https://github.com/mostafatalaat770)
- **Ahmed Swidan** - [ahmed-swidan](https://github.com/ahmed-swidan)
