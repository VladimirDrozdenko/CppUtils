//
// Created by Drozdenko, Vladimir on 4/13/23.
//

#ifndef ACA4CAE16F2E40FA9032548D78D4AE3D_H
#define ACA4CAE16F2E40FA9032548D78D4AE3D_H

#include <string>

template <char DELIM>
class DelimiterStringIterator
{
public:
    DelimiterStringIterator() : pb_(nullptr), pe_(nullptr) {
    }
    explicit DelimiterStringIterator(const char* str) : pb_(str), pe_(strchr(str, DELIM)) {
    }
    explicit DelimiterStringIterator(const std::string& str) : pb_(str.c_str()), pe_(strchr(str.c_str(), DELIM)) {
    }
    DelimiterStringIterator(const DelimiterStringIterator<DELIM>& itr) : pb_(itr.pb_), pe_(itr.pe_) {
    }
    DelimiterStringIterator& operator = (const DelimiterStringIterator<DELIM>& itr) {
        if (this != &itr) {
            pb_ = itr.pb_, pe_ = itr.pe_;
        }
        return *this;
    }

    friend bool operator == (const DelimiterStringIterator<DELIM>& itr1, const DelimiterStringIterator<DELIM>& itr2) {
        return itr1.pb_ == itr2.pb_ && itr1.pe_ == itr2.pe_;
    }

    friend bool operator != (const DelimiterStringIterator<DELIM>& itr1, const DelimiterStringIterator<DELIM>& itr2) {
        return itr1.pb_ != itr2.pb_ || itr1.pe_ != itr2.pe_;
    }

    std::string operator * () const {
        if (!pb_) {
            throw std::out_of_range("attempt to dereference end() iterator");
        }

        if (pe_) {
            return {pb_, pe_};
        }
        return std::string(pb_);
    }

    DelimiterStringIterator& operator ++ () {
        if (!pb_) {
            assert(pe_ == nullptr); // check internal consistency
            assert(false); // this is logically incorrect to increment end-iterator
            return *this;
        }

        if (!pe_) {
            pb_ = nullptr;
            return *this;
        }

        pb_ = pe_ + 1;
        pe_ = strchr(pb_, DELIM);
        return *this;
    }

    DelimiterStringIterator operator ++ (int) {
        DelimiterStringIterator tmp = *this;
        ++(*this);
        return tmp;
    }

private:
    const char* pb_;
    const char* pe_;
};


#endif // ACA4CAE16F2E40FA9032548D78D4AE3D_H
