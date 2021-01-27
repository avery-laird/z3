/*++
Copyright (c) 2011 Microsoft Corporation

Module Name:

    char_decl_plugin.h

Abstract:

    char_plugin for unicode suppport

Author:

    Nikolaj Bjorner (nbjorner) 2011-11-14

Revision History:

    Updated to string sequences 2015-12-5

    Add SMTLIB 2.6 support 2020-5-17

--*/
#pragma once

#include "ast/ast.h"
#include "ast/bv_decl_plugin.h"
#include <string>

enum char_sort_kind {
    CHAR_SORT
};

enum char_op_kind {
    OP_CHAR_CONST,
    OP_CHAR_LE
};

class char_decl_plugin : public decl_plugin {
    sort* m_char { nullptr };
    symbol m_charc_sym;

    void set_manager(ast_manager * m, family_id id) override;

public:
    char_decl_plugin();

    ~char_decl_plugin() override {}

    void finalize() override {}

    decl_plugin* mk_fresh() override { return alloc(char_decl_plugin); }

    sort* mk_sort(decl_kind k, unsigned num_parameters, parameter const* parameters) override { return m_char; }

    func_decl* mk_func_decl(decl_kind k, unsigned num_parameters, parameter const* parameters,
        unsigned arity, sort* const* domain, sort* range) override;

    void get_op_names(svector<builtin_name>& op_names, symbol const& logic) override;

    void get_sort_names(svector<builtin_name>& sort_names, symbol const& logic) override;

    bool is_value(app* e) const override;

    bool is_unique_value(app* e) const override;

    bool are_equal(app* a, app* b) const override;

    bool are_distinct(app* a, app* b) const override;

    app* mk_char(unsigned u);

    expr* get_some_value(sort* s) override;
};
