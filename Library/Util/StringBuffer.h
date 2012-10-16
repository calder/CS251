/// A dynamically growable string
struct
{
    char* data;
    int length;
    int capacity;
}
typedef StringBuffer;


/// Malloc, initialize and return an empty StringBuffer
StringBuffer* strbuf_create ();

/// Empty the StringBuffer
/// @note This does not reduce the capacity or memory footprint of the
/// StringBuffer.
void strbuf_clear (StringBuffer* buf);

/// Free the StringBuffer's memory
void strbuf_free (StringBuffer* buf);

/// Display the entire StringBuffer
void strbuf_print (StringBuffer* buf);

/// Return the current string value of the StringBuffer
const char* strbuf_data (StringBuffer* buf);

/// Return the number of characters in the StringBuffer (excluding terminator)
int strbuf_len (StringBuffer* buf);

/// Add a single character to the end of the StringBuffer
void strbuf_append (StringBuffer* buf, char c);

/// Add a string to the end of the StringBuffer
void strbuf_append_string (StringBuffer* buf, const char* string);