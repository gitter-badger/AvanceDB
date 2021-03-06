#ifndef GET_ALL_DOCUMENTS_OPTIONS_H
#define	GET_ALL_DOCUMENTS_OPTIONS_H

#include <string>

#include <boost/optional.hpp>

#include "libhttpserver.h"

#include "types.h"

class GetAllDocumentsOptions final {
public:
    GetAllDocumentsOptions(const rs::httpserver::QueryString& qs);
    
    bool HasKey() const;
    bool HasKeys() const;
    
    const std::string& Key() const;
    const std::string& StartKey() const;
    const std::string& StartKeyDocId() const;
    const std::string& EndKey() const;
    const std::string& EndKeyDocId() const;
    
    bool Descending() const;
    bool IncludeDocs() const;
    bool InclusiveEnd() const;
    bool UpdateSequence() const;
    
    uint64_t Skip() const;
    uint64_t Limit() const;
    
private:
    std::string GetString(const char* name, const char* altName = nullptr) const;
    bool GetBoolean(const char* name, bool defaultValue) const;
    uint64_t GetUnsigned(const char* name, uint64_t defaultValue) const;
    
    mutable std::string key_;
    mutable std::string startKey_;
    mutable std::string startKeyDocId_;
    mutable std::string endKey_;
    mutable std::string endKeyDocId_;
        
    mutable boost::optional<bool> conflicts_;
    mutable boost::optional<bool> descending_;
    mutable boost::optional<bool> includeDocs_;
    mutable boost::optional<bool> inclusiveEnd_;
    mutable boost::optional<bool> updateSequence_;
    
    mutable boost::optional<uint64_t> skip_;
    mutable boost::optional<uint64_t> limit_;
    
    const rs::httpserver::QueryString& qs_;
};

#endif	/* GET_ALL_DOCUMENTS_OPTIONS_H */

