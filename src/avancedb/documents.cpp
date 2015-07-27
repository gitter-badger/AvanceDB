#include "documents.h"

#include <boost/bind.hpp>

#include "document.h"
#include "rest_exceptions.h"

Documents::Documents(database_ptr db) : db_(db) {
    
}

documents_ptr Documents::Create(database_ptr db) {
    return documents_ptr(new Documents(db));
}

Documents::collection::size_type Documents::getCount() {
    return docs_.size();
}

document_ptr Documents::GetDocument(const char* id) {
    Document::Compare compare{id};
    auto doc = docs_.find_fn(compare);
    
    if (!doc) {
        throw DocumentMissing();
    }
    
    return doc;
}

document_ptr Documents::SetDocument(const char* id, script_object_ptr obj) {
    Document::Compare compare{id};
    auto doc = docs_.find_fn(compare);

    if (!!doc) {
        if (obj->getType("_rev") != rs::scriptobject::ScriptObjectType::String) {
            throw DocumentConflict();
        }
        
        auto objRev = obj->getString("_rev");
        
        auto docRev = doc->getRev();
        
        if (std::strcmp(objRev, docRev) != 0) {
            throw DocumentConflict();
        }
    }

    doc = Document::Create(id, obj);

    docs_.insert(doc);

    return doc;
}