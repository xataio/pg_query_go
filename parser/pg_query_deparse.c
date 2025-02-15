#include "pg_query.h"
#include "pg_query_internal.h"
#include "pg_query_readfuncs.h"

#include "postgres_deparse.h"

PgQueryDeparseResult pg_query_deparse_protobuf(PgQueryProtobuf parse_tree)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	List *stmts;
	ListCell *lc;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		stmts = pg_query_protobuf_to_nodes(parse_tree);

		initStringInfo(&str);

		foreach(lc, stmts) {
			deparseRawStmt(&str, castNode(RawStmt, lfirst(lc)));
			if (lnext(stmts, lc))
				appendStringInfoString(&str, "; ");
		}
		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_expr_protobuf(PgQueryProtobuf expr)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	Node *node;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		node = pg_query_protobuf_to_node(expr);

		initStringInfo(&str);

		deparseExpr(&str, node);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_typename_protobuf(PgQueryProtobuf expr)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
  TypeName *typename;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		typename = pg_query_protobuf_to_typename(expr);

		initStringInfo(&str);

    deparseTypeName(&str, typename);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_reloptions_protobuf(PgQueryProtobuf buf)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	List *list;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		list = pg_query_protobuf_to_list(buf);

		initStringInfo(&str);

		deparseRelOptions(&str, list);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_parenthesized_seq_opt_list_protobuf(PgQueryProtobuf buf)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	List *list;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		list = pg_query_protobuf_to_list(buf);

		initStringInfo(&str);

		deparseOptParenthesizedSeqOptList(&str, list);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_any_operator_protobuf(PgQueryProtobuf buf)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	List *list;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		list = pg_query_protobuf_to_list(buf);

		initStringInfo(&str);

		deparseAnyOperator(&str, list);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

PgQueryDeparseResult pg_query_deparse_index_elem_protobuf(PgQueryProtobuf buf)
{
	PgQueryDeparseResult result = {0};
	StringInfoData str;
	MemoryContext ctx;
	Node *node;

	ctx = pg_query_enter_memory_context();

	PG_TRY();
	{
		node = pg_query_protobuf_to_node(buf);

		initStringInfo(&str);

		deparseIndexElem(&str, node);

		result.query = strdup(str.data);
	}
	PG_CATCH();
	{
		ErrorData* error_data;
		PgQueryError* error;

		MemoryContextSwitchTo(ctx);
		error_data = CopyErrorData();

		// Note: This is intentionally malloc so exiting the memory context doesn't free this
		error = malloc(sizeof(PgQueryError));
		error->message   = strdup(error_data->message);
		error->filename  = strdup(error_data->filename);
		error->funcname  = strdup(error_data->funcname);
		error->context   = NULL;
		error->lineno	= error_data->lineno;
		error->cursorpos = error_data->cursorpos;

		result.error = error;
		FlushErrorState();
	}
	PG_END_TRY();

	pg_query_exit_memory_context(ctx);

	return result;
}

void pg_query_free_deparse_result(PgQueryDeparseResult result)
{
	if (result.error) {
		pg_query_free_error(result.error);
	}

	free(result.query);
}
