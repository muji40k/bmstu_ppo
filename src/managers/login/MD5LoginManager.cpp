#include "MD5LoginManager.h"

static void free_res(EVP_MD_CTX *&ctx, unsigned char *&digest)
{
    if (nullptr != ctx)
    {
        EVP_MD_CTX_free(ctx);
        ctx = nullptr;
    }

    if (nullptr != digest)
    {
        OPENSSL_free(digest);
        digest = nullptr;
    }
}

class WrapFreeException : public ManagerException
{
    public:
        WrapFreeException(ManagerException *wrapped, EVP_MD_CTX *ctx,
                          unsigned char *digest)
            : wrapped(wrapped),
              ctx(ctx),
              digest(digest)
        {}

        virtual ~WrapFreeException(void)
        {
            delete wrapped;
        }

        EVP_MD_CTX *&getCTX(void)
        {
            return this->ctx;
        }

        unsigned char *&getDigest(void)
        {
            return this->digest;
        }

        ManagerException &getException(void)
        {
            return *this->wrapped;
        }

    private:
        ManagerException *wrapped;
        EVP_MD_CTX *ctx;
        unsigned char *digest;
};

std::string MD5LoginManager::hash(const User &user)
try
{
    std::string bufstring = std::to_string(user.id) + user.name \
                            + user.password + user.email;
    const unsigned char *buf = (const unsigned char *)bufstring.c_str();

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    unsigned char *md5_digest = nullptr;

    if (nullptr == ctx)
        throw WrapFreeException(new CALL_EX(MD5AllocationException), ctx,
                                md5_digest);

    if (!EVP_DigestInit_ex(ctx, EVP_md5(), NULL))
        throw WrapFreeException(new CALL_EX(MD5HashInnerException), ctx,
                                md5_digest);

    if (!EVP_DigestUpdate(ctx, buf, bufstring.size()))
        throw WrapFreeException(new CALL_EX(MD5HashInnerException), ctx,
                                md5_digest);

    unsigned int md5_digest_len = EVP_MD_size(EVP_md5());
    md5_digest = (unsigned char *)OPENSSL_malloc(md5_digest_len);

    if (nullptr == md5_digest)
        throw WrapFreeException(new CALL_EX(MD5AllocationException), ctx,
                                md5_digest);

    if (!EVP_DigestFinal_ex(ctx, md5_digest, &md5_digest_len))
        throw WrapFreeException(new CALL_EX(MD5HashInnerException), ctx,
                                md5_digest);

    std::stringstream stream;

    for (size_t i = 0; md5_digest_len > i; i++)
        stream << std::hex << std::setw(2) << std::setfill('0')
               << static_cast<int>(md5_digest[i]);

    free_res(ctx, md5_digest);

    return stream.str();
}
catch (WrapFreeException &er)
{
    free_res(er.getCTX(), er.getDigest());

    throw er.getException();
}

