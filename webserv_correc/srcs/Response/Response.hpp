#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
# include "request_class.hpp"

class Response {

enum return_codes{UNSET=0, OK=200, NOT_IMPLEMENTED=501, INTERNAL_ERROR=500, NOT_FOUND=404, REDIR=301, FORBIDDEN=403};
#define YES 1
#define ERROR 2
#define NO 0
#define DONE 0
#define CONTINUE 1

private:
    typedef std::map<std::string, std::string> str_map;
    typedef std::map<int, std::string> int_map;

    const Request               &req;
    std::string                 headers;
    std::vector<unsigned char>  &response;
    int                         response_code; 
    std::string                 extension; 
    std::string                 target; 
    bool                        redir_activated;
    std::string                 redir_target;
    
    static str_map extension_map;
    static str_map init_ext_map();
    static int_map code_map;
    static int_map init_code_map();
    static std::string delete_response;

    void build_response_line();
    void set_extension_from_target();
    void build_target();
    std::string get_content_type();
    void build_response();
    void build_headers();
    void build_content_length();
    void build_keep_alive();
    void build_content_type();
    void build_location_if_redirection();
    void get_module();
    void put_module();
    std::string build_index_uri(std::string index);
    int remove_target();
    int target_exists();
    int read_and_store_target_content();
    void store_default_error_message();
    int try_index_directive();
    int check_target_is_directory();
    int handle_directory_target_with_no_trailing_slash();
    void check_errno_and_send_error(int error_num);
    void delete_module();
    void index_module();
    void autoindex_module();
    void file_module();
    void error_module(int error_code);
    void cgi_module();
    void send_img(std::string const& path);
    bool is_cgi_extension();
    void redir_module(int redir_code, std::string redir_target);

    
    Response(void);

public:
    Response(const Request &req, std::vector<unsigned char> &buf);
    Response(Response const & copy);
    ~Response(void);
    Response& operator=(Response const & rhs);

    int build();

    /* getters */
    const std::string& getTarget(void) const;
};

int uri_is_directory(std::string uri);
int uri_is_file(std::string uri);
int uri_exists(std::string uri);
std::ostream & operator<<(std::ostream & o, Response const & rhs);

#endif // RESPONSE_HPP
