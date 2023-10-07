#ifndef _IADMINMODEL_H_
#define _IADMINMODEL_H_

#include <list>

#include <memory>
#include <string>
#include <unordered_map>

#include "model_exception.h"

class IAdminModel
{
    public:
        using Map = std::unordered_map<std::string, std::string>;
        using CriteriaMap = struct
        {
            std::string field;
            std::string op;
            std::string value;
        };

        class InnerIter
        {
            public:
                virtual ~InnerIter(void) = default;
                virtual void next(void) = 0;
                virtual Map get(void) const = 0;
                virtual bool notEqual(std::shared_ptr<const InnerIter> iter) const = 0;
        };
        class InnerSet
        {
            public:
                virtual ~InnerSet(void) = default;
                virtual std::shared_ptr<InnerIter> begin(void) = 0;
                virtual std::shared_ptr<InnerIter> end(void) = 0;
        };

        class Iterator
        {
            public:
                Iterator (std::shared_ptr<InnerIter> iter);
                Map operator * (void) const;
                Iterator &operator ++ (void);
                bool operator != (const Iterator &iter) const;

            private:
                std::shared_ptr<InnerIter> iter;
        };
        class Set
        {
            public:
                Set(std::shared_ptr<InnerSet> set);
                Iterator begin(void);
                Iterator end(void);

            private:
                std::shared_ptr<InnerSet> set;
        };

        class Mapper
        {
            public:
                virtual ~Mapper(void) = default;
                virtual void create(std::string hash, Map map) = 0;
                virtual void update(std::string hash, Map map) = 0;
                virtual void remove(std::string hash, Map map) = 0;
                virtual void remove(std::string hash, std::list<CriteriaMap> criterias) = 0;
                virtual Set get(std::string hash, std::list<CriteriaMap> criterias) = 0;
                virtual Map getEmptyMap(void) = 0;
        };

    public:
        virtual ~IAdminModel(void) = default;
        virtual bool isAdmin(std::string hash) const = 0;
        virtual Set getRequests(std::string hash) = 0;
        virtual void setRequest(std::string hash, Map map) = 0;

        void create(std::string hash, std::string name, Map map);
        void update(std::string hash, std::string name, Map map);
        void remove(std::string hash, std::string name, Map map);
        void remove(std::string hash, std::string name, std::list<CriteriaMap> criterias);
        Set get(std::string hash, std::string name, std::list<CriteriaMap> criterias);

        Map getEmptyMap(std::string name);

        void add(std::string name, std::shared_ptr<Mapper> mapper);

    private:
        std::unordered_map<std::string, std::shared_ptr<Mapper>> mappers;
};

DEF_EX(CommonAdminModelException, ModelException, "Common AdminModel exception");
DEF_EX(NullptrAdminModelException, CommonAdminModelException, "Nullptr occured");
DEF_EX(NotAuthenticatedAdminModelException, CommonAdminModelException, "User not authenticated");
DEF_EX(NotAuthorizedAdminModelException, CommonAdminModelException, "User not authorized");
DEF_EX(NoHandlerAdminModelException, CommonAdminModelException, "Handler for type not set");
DEF_EX(RedirectAdminModelException, CommonAdminModelException, "");

#endif

